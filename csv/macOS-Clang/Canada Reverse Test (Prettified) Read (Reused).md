
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1271.71 | 0.771065 | 7671.07ms | 5212421 | 30 | 2.72524e+10 | 3.90887e+06 | 0.283736 | 1(Win) | true |
| simdjson (ondemand) | 954.518 | 1.14609 | 8562.14ms | 5212421 | 40 | 1.42498e+11 | 5.20781e+06 | 0.179933 | 2(Loss) | true |
