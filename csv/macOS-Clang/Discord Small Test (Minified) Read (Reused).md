
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2606.51 | 0.150951 | 208.329ms | 4857 | 80 | 575.676 | 1777.09 | 1.67169 | 1(Win) | true |
| Glaze | 1685.69 | 0.247702 | 290.708ms | 4857 | 2560 | 118599 | 2747.83 | 0.392472 | 2(Loss) | true |
| Jsonifier (two-stage) | 1512.65 | 0.282978 | 368.244ms | 4857 | 4890 | 367176 | 3062.17 | 1.67902 | 3(Loss) | true |
| simdjson (ondemand) | 679.783 | 0.267012 | 716.727ms | 4857 | 30 | 9930.69 | 6813.93 | 0.37071 | 4(Loss) | true |
