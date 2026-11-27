
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1388.25 | 0.182486 | 4630.13ms | 65103 | 160 | 1.06572e+06 | 44723.2 | 0.0429123 | 1(Win) | true |
| simdjson (ondemand) | 1021.38 | 0.131835 | 6281.51ms | 65103 | 640 | 4.11025e+06 | 60787.2 | 0.275612 | 2(Loss) | true |
