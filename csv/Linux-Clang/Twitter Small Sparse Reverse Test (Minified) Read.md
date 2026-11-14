
----
### Twitter Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4088.8 | 0.0437061 | 778.493ms | 2821 | 4890 | 404.397 | 657.972 | 0.135502 | 1.33332 | 5.43283 | 0.868132 | 0.00125237 | 2.73294e-05 | 1.81229e-06 | 1(Win) | true |
| simdjson (ondemand) | 3807.09 | 0.0438745 | 784.565ms | 2821 | 2560 | 246.084 | 706.659 | 0.194916 | 1.43098 | 6.24991 | 0.899681 | 0.000850624 | 1.53702e-05 | 2.49247e-06 | 2(Loss) | true |
