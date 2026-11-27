
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 989.283 | 0.647117 | 7590.21ms | 4212000 | 80 | 5.5232e+10 | 4.06039e+06 | 5.5928 | 3.07211 | -(Win) | false |
| simdjson (ondemand) | 899.501 | 0.307707 | 8309.43ms | 4212000 | 80 | 1.51056e+10 | 4.46567e+06 | 0.163231 | 3.37877 | 2(Loss) | true |
