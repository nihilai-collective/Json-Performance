
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3013.9 | 0.309608 | 3219.79ms | 83958 | 320 | 2.16491e+06 | 26566.4 | 0.479501 | 1(Win) | true |
| simdjson (ondemand) | 2227.25 | 0.188055 | 3915.03ms | 83958 | 640 | 2.92509e+06 | 35949.6 | 0.176111 | 2(Loss) | true |
