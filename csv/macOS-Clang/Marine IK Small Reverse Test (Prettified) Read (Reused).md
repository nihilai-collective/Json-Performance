
----
### Marine IK Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 892.362 | 0.335053 | 2076.87ms | 18245 | 640 | 2.73158e+06 | 19498.6 | 0.0714685 | 1(Win) | true |
| simdjson (ondemand) | 646.873 | 0.054052 | 2892.4ms | 18245 | 4890 | 1.03367e+06 | 26898.3 | 0.133036 | 2(Loss) | true |
