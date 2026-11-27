
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 851.673 | 0.206004 | 5965.48ms | 53331 | 4890 | 7.40074e+07 | 59718.2 | 0.0673834 | 3.56721 | 1(Win) | true |
| simdjson (ondemand) | 717.24 | 0.15482 | 7244.42ms | 53331 | 640 | 7.71371e+06 | 70911.2 | 0.314317 | 4.23611 | 2(Loss) | true |
