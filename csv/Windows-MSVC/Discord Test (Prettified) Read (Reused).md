
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2222.45 | 0.322612 | 4242.69ms | 83958 | 320 | 4.32286e+06 | 36027.2 | 0.434407 | 1.11324 | 1(Win) | true |
| Glaze | 1894.71 | 0.149757 | 4927.13ms | 83958 | 1280 | 5.1265e+06 | 42259 | 0.0231143 | 1.30584 | 2(Loss) | true |
| Jsonifier (two-stage) | 1750.57 | 0.0890684 | 5302.62ms | 83958 | 4890 | 8.11565e+06 | 45738.7 | 0.267198 | 1.41337 | 3(Loss) | true |
| simdjson (ondemand) | 1403.86 | 0.0752404 | 6276.5ms | 83958 | 4890 | 9.00509e+06 | 57034.6 | 0.54036 | 1.7627 | 4(Loss) | true |
