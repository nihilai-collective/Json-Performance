
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 976.903 | 0.391021 | 6333.86ms | 65103 | 4890 | 3.02e+08 | 63555 | 0.239646 | 3.1098 | 1(Win) | true |
| simdjson (ondemand) | 836.144 | 0.740967 | 7393.4ms | 65103 | 1280 | 3.87479e+08 | 74254.1 | 0.334925 | 3.63365 | 2(Loss) | true |
