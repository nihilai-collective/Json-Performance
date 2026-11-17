
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1624.82 | 0.0607315 | 5367.01ms | 83958 | 2560 | 2.29287e+06 | 49278.3 | 0.0837173 | 1.86957 | 1(Win) | true |
| simdjson (ondemand) | 1430.48 | 0.464189 | 6102.99ms | 83958 | 2560 | 1.72819e+08 | 55973.3 | 0.264916 | 2.12382 | 2(Loss) | true |
