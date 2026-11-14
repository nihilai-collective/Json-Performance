
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1354.44 | 0.0382446 | 3982.38ms | 56369 | 4890 | 1.1267e+06 | 39689.9 | 0.213278 | 2.24251 | 1(Win) | true |
| Glaze | 1172.7 | 0.0414264 | 4585.24ms | 56369 | 4890 | 1.76347e+06 | 45840.9 | 0.0651929 | 2.59029 | 2(Loss) | true |
| Jsonifier (two-stage) | 1092.73 | 0.0372202 | 4912.6ms | 56369 | 4890 | 1.63953e+06 | 49195.7 | 0.205363 | 2.77984 | 3(Loss) | true |
| simdjson (ondemand) | 768.914 | 0.129511 | 7045.15ms | 56369 | 80 | 655884 | 69913.8 | 0.0232375 | 3.95138 | 4(Loss) | true |
