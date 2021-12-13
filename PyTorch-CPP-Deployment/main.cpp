#include <torch/torch.h>
#include <torch/script.h>
#include "folder_reader.h"
#include "dataset.h"

int main(int argc, char *argv[]){
    std::string path_to_folder = argv[1];
    //declares the batch size, can be increased or decreased depending upon size of GPU
    int batch_size = 32;
    //checks in CUDA is available or not
    auto cuda_available = torch::cuda::is_available();
    torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);
    std::cout << (cuda_available ? "CUDA available. Infering on GPU." : "Infering on CPU.") <<std::endl;
    //loads the model into memory
    std::cout << "Loading model" <<std::endl;
    torch::jit::script::Module module;
    module = torch::jit::load("/usr/local/LENS-DEPLOY/PyTorch-CPP-Deployment/demo-model.pt");
    //comment out this line if CUDA is not available
    module.to(at::kCUDA);
    std::cout<<"Model loaded"<<std::endl;
    //creates the dataset and dataloader
    auto data_set = image_dataset(path_to_folder).map(torch::data::transforms::Stack<>());
    auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
        data_set,
        batch_size);
    //placeholder tensors for outputs
    std::vector<torch::jit::IValue> outputs_array;
    //performs batch wise inference
    for(auto& batch : *data_loader){
	std::cout<<"Infering on a batch"<<std::endl;
	auto images = batch.data.to(device);
	images.to(torch::kF32);
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(images);
    at::Tensor output = module.forward(inputs).toTensor();
    //prints the output
	std::cout << output << '\n';
    outputs_array.push_back(output);
    }
}