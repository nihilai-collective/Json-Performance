
----
### Random Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 464.379 | 0.781852 | 8987.75ms | 4506447 | 40 | 2.09427e+11 | 9.25469e+06 | 1.25986 | 5.33129 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 242.2 | 3.4827 | 6233.53ms | 4506447 | 30 | 1.14571e+13 | 1.77444e+07 | 6.80963 | 10.2221 | -(Loss) | false |
