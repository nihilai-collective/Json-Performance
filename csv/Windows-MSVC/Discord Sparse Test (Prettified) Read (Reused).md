
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2850.02 | 0.0956273 | 3250.7ms | 83958 | 4890 | 3.52939e+06 | 28094 | 0.0866025 | 1.06547 | 1(Win) | true |
| simdjson (ondemand) | 2721.92 | 0.186535 | 3391.4ms | 83958 | 80 | 240872 | 29416.2 | 0.0297366 | 1.11565 | 2(Loss) | true |
