
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2886.37 | 0.037729 | 3178.75ms | 83958 | 4890 | 535647 | 27740.2 | 0.183079 | 1.05201 | 1(Win) | true |
| simdjson (ondemand) | 2536.33 | 0.0693383 | 3558.9ms | 83958 | 4890 | 2.34299e+06 | 31568.7 | 0.304396 | 1.1974 | 2(Loss) | true |
