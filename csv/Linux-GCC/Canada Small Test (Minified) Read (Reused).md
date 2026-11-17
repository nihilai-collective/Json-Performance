
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1097.57 | 0.0497141 | 484.985ms | 4630 | 40 | 160 | 4023 | 0.0910596 | 2.24016 | 1(Win) | true |
| Jsonifier (two-stage) | 1035.93 | 0.0618936 | 506.859ms | 4630 | 30 | 208.792 | 4262.37 | 0.0390866 | 2.37553 | 2(Loss) | true |
| Glaze | 876.694 | 0.0865364 | 592.397ms | 4630 | 40 | 759.844 | 5036.55 | 0.101031 | 2.80875 | 3(Loss) | true |
| simdjson (reflection) | 763.45 | 0.14909 | 673.893ms | 4630 | 30 | 2230.59 | 5783.63 | 0.150199 | 3.22706 | 4(Loss) | true |
| simdjson (ondemand) | 758.778 | 0.171152 | 674.162ms | 4630 | 4890 | 485068 | 5819.24 | 0.219257 | 3.24759 | 5(Loss) | true |
