// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: movements.proto

#include "movements.pb.h"
#include "movements.grpc.pb.h"

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

static const char* MovementService_method_names[] = {
  "/MovementService/Move",
};

std::unique_ptr< MovementService::Stub> MovementService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MovementService::Stub> stub(new MovementService::Stub(channel, options));
  return stub;
}

MovementService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Move_(MovementService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MovementService::Stub::Move(::grpc::ClientContext* context, const ::MovementRequest& request, ::MovementResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::MovementRequest, ::MovementResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Move_, context, request, response);
}

void MovementService::Stub::async::Move(::grpc::ClientContext* context, const ::MovementRequest* request, ::MovementResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::MovementRequest, ::MovementResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Move_, context, request, response, std::move(f));
}

void MovementService::Stub::async::Move(::grpc::ClientContext* context, const ::MovementRequest* request, ::MovementResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Move_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::MovementResponse>* MovementService::Stub::PrepareAsyncMoveRaw(::grpc::ClientContext* context, const ::MovementRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::MovementResponse, ::MovementRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Move_, context, request);
}

::grpc::ClientAsyncResponseReader< ::MovementResponse>* MovementService::Stub::AsyncMoveRaw(::grpc::ClientContext* context, const ::MovementRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncMoveRaw(context, request, cq);
  result->StartCall();
  return result;
}

MovementService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MovementService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MovementService::Service, ::MovementRequest, ::MovementResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MovementService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::MovementRequest* req,
             ::MovementResponse* resp) {
               return service->Move(ctx, req, resp);
             }, this)));
}

MovementService::Service::~Service() {
}

::grpc::Status MovementService::Service::Move(::grpc::ServerContext* context, const ::MovementRequest* request, ::MovementResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


