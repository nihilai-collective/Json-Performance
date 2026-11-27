
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 893.225 | 0.0626946 | 9190.09ms | 83958 | 2560 | 8.08544e+06 | 89639.9 | 0.0679607 | 1(Win) | true |
| simdjson (ondemand) | 215.952 | 0.109496 | 9586.65ms | 83958 | 640 | 1.05483e+08 | 370770 | 0.365013 | 2(Loss) | true |
