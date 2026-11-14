
----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3264.93 | 0.0407603 | 863.647ms | 4857 | 4890 | 1635.21 | 1418.71 | 0.164409 | 1.62126 | 6.94668 | 1.19971 | 0.00105193 | 2.98096e-05 | 2.31572e-06 | 1(Win) | true |
| simdjson (ondemand) | 2411.77 | 0.0440764 | 911.48ms | 4857 | 2560 | 1834.49 | 1920.58 | 0.12885 | 2.17989 | 9.69055 | 1.58308 | 0.00265821 | 1.69697e-05 | 3.45828e-06 | 2(Loss) | true |
