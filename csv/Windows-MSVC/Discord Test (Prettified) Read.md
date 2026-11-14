
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21571.7 | 0.231516 | 380.904ms | 83958 | 4890 | 361098 | 3711.74 | 0.0310374 | 0.113977 | 1(Win) | true |
| simdjson (stage-1) | 19469.6 | 0.128772 | 424.129ms | 83958 | 40 | 1121.79 | 4112.5 | 0.0202593 | 0.12613 | 2(Loss) | true |
