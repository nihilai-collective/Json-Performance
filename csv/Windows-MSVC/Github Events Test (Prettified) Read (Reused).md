
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1616.42 | 0.371652 | 4655.19ms | 65103 | 320 | 6.52105e+06 | 38410.3 | 0.338117 | 1.53034 | 1(Win) | true |
| Glaze | 1491.02 | 0.204088 | 4821.42ms | 65103 | 4890 | 3.53165e+07 | 41640.7 | 0.62354 | 1.65934 | 2(Loss) | true |
| Jsonifier | 1426.15 | 0.128792 | 5161.42ms | 65103 | 2560 | 8.0481e+06 | 43534.9 | 0.0956505 | 1.73487 | 3(Loss) | true |
| simdjson (ondemand) | 893.005 | 0.204818 | 7703.25ms | 65103 | 2560 | 5.19123e+07 | 69526 | 0.215423 | 2.77127 | 4(Loss) | true |
