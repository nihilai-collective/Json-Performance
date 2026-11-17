
----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4681.31 | 0.0956046 | 830.025ms | 4857 | 4890 | 4375.9 | 989.465 | 0.00278246 | 1.12869 | 4.95882 | 0.756434 | 0.000574803 | 2.73255e-05 | 1.26733e-05 | 1(Win) | true |
| simdjson (ondemand) | 3939.57 | 0.0751818 | 866.034ms | 4857 | 4890 | 3820.97 | 1175.76 | 0.160375 | 1.34886 | 5.4616 | 0.707433 | 0.00104207 | 5.41878e-05 | 2.20204e-05 | 2(Loss) | true |
