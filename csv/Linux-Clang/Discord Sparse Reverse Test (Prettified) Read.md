
----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2491.75 | 0.0888382 | 3955.32ms | 83958 | 80 | 65193.5 | 32133.5 | 0.0176965 | 2.06846 | 9.71114 | 1.73789 | 0.00444448 | 6.99755e-06 | 2.38214e-06 | 1(Win) | true |
| simdjson (ondemand) | 1898.49 | 0.03005 | 4947.57ms | 83958 | 4890 | 785432 | 42175 | 0.0379746 | 2.70094 | 12.0205 | 1.94246 | 0.00610813 | 8.32045e-06 | 3.37105e-06 | 2(Loss) | true |
