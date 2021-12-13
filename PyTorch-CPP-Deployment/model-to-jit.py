import torch
import torchvision

#create instance of model here
#using pre-trained resnet18 model for demonstration
model = torchvision.models.resnet18(pretrained=True)

#turn on eval mode for the model
model.eval()

#example input array for the model
example = torch.rand(1, 3, 224, 224)

#use torch.jit.trace to generate a torch.jit.ScriptModule via tracing
traced_script_module = torch.jit.trace(model, example)

#saves the jit model
traced_script_module.save("demo-model.pt")