
----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1925.13 | 0.0717897 | 967.975ms | 4926 | 640 | 1964.15 | 2440.25 | 0.0690081 | 2.72012 | 12.0481 | 2.29781 | 0.00407468 | 3.04507e-05 | 1.01502e-05 | 1(Win) | true |
| simdjson (ondemand) | 1576.59 | 0.0594957 | 1017.56ms | 4926 | 2560 | 8045.68 | 2979.72 | 0.0582507 | 3.31524 | 14.6186 | 2.44742 | 0.00487195 | 3.45742e-05 | 1.40359e-05 | 2(Loss) | true |
