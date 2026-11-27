
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 861.353 | 1.32158 | 111.718ms | 905 | 640 | 112229 | 1002 | 0.280224 | 1(Win) | true |
| simdjson (ondemand) | 400.165 | 0.359977 | 223.403ms | 905 | 2560 | 154316 | 2156.8 | 0.46151 | 2(Loss) | true |
