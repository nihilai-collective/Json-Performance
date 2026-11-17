
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4335.71 | 1.26249 | 91.765ms | 3808 | 1280 | 143133 | 837.6 | 0.0477327 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4295.56 | 0.671578 | 92.798ms | 3808 | 4890 | 157636 | 845.428 | 1.3042 | 1(Tie) | true |
| simdjson (reflection) | 4200.88 | 0.623679 | 91.8162ms | 3808 | 4890 | 142150 | 864.484 | 0.691068 | 3(Loss) | true |
| simdjson (ondemand) | 4099.34 | 0.639788 | 94.537ms | 3808 | 4890 | 157089 | 885.896 | 1.47952 | 4(Loss) | true |
| Glaze | 2897.62 | 0.658632 | 130.888ms | 3808 | 4890 | 333200 | 1253.3 | 1.12027 | 5(Loss) | true |
