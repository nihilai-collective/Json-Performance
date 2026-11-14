
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1575.95 | 0.0889697 | 5697.48ms | 83958 | 4890 | 9.99156e+06 | 50806.6 | 0.518303 | 1.56987 | 1(Win) | true |
| simdjson (ondemand) | 1229.97 | 0.40388 | 6959.16ms | 83958 | 160 | 1.10602e+07 | 65098.1 | 0.0105599 | 2.01201 | 2(Loss) | true |
