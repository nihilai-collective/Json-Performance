
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 591.416 | 0.481184 | 5044.28ms | 4219120 | 30 | 3.21515e+10 | 6.80344e+06 | 0.184413 | 5.13887 | 1(Win) | true |
| simdjson (ondemand) | 220.226 | 0.218453 | 5640.44ms | 4219120 | 30 | 4.77909e+10 | 1.82706e+07 | 0.188999 | 13.8012 | 2(Loss) | true |
