// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: com.proto

#include "com.pb.h"
#include "com.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>

static const char* Greeter_method_names[] = {
  "/Greeter/SayHello",
};

std::unique_ptr< Greeter::Stub> Greeter::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Greeter::Stub> stub(new Greeter::Stub(channel, options));
  return stub;
}

Greeter::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SayHello_(Greeter_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Greeter::Stub::SayHello(::grpc::ClientContext* context, const ::HelloRequest& request, ::HelloResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::HelloRequest, ::HelloResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SayHello_, context, request, response);
}

void Greeter::Stub::async::SayHello(::grpc::ClientContext* context, const ::HelloRequest* request, ::HelloResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::HelloRequest, ::HelloResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SayHello_, context, request, response, std::move(f));
}

void Greeter::Stub::async::SayHello(::grpc::ClientContext* context, const ::HelloRequest* request, ::HelloResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SayHello_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::HelloResponse>* Greeter::Stub::PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, const ::HelloRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::HelloResponse, ::HelloRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SayHello_, context, request);
}

::grpc::ClientAsyncResponseReader< ::HelloResponse>* Greeter::Stub::AsyncSayHelloRaw(::grpc::ClientContext* context, const ::HelloRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSayHelloRaw(context, request, cq);
  result->StartCall();
  return result;
}

Greeter::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Greeter_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Greeter::Service, ::HelloRequest, ::HelloResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Greeter::Service* service,
             ::grpc::ServerContext* ctx,
             const ::HelloRequest* req,
             ::HelloResponse* resp) {
               return service->SayHello(ctx, req, resp);
             }, this)));
}

Greeter::Service::~Service() {
}

::grpc::Status Greeter::Service::SayHello(::grpc::ServerContext* context, const ::HelloRequest* request, ::HelloResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


