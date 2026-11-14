
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1254.72 | 0.342474 | 7279.09ms | 5212421 | 40 | 7.36382e+09 | 3.96181e+06 | 1.19355 | 1(Win) | true |
| simdjson (ondemand) | 1124.69 | 0.839649 | 7448.85ms | 5212421 | 80 | 1.10179e+11 | 4.41984e+06 | 1.19356 | 2(Loss) | true |
