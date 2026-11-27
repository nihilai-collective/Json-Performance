
----
### Amazon Cellphones Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3821.53 | 0.165856 | 7041.63ms | 277673 | 320 | 4.22676e+06 | 69294.2 | 0.0179927 | 1(Win) | true |
| simdjson (ondemand) | 3155.13 | 0.059825 | 8461.59ms | 277673 | 4890 | 1.23284e+07 | 83929.8 | 0.286558 | 2(Loss) | true |
