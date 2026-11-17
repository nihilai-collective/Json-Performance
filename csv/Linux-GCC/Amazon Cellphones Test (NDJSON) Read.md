
----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5860.04 | 0.0807933 | 5260.06ms | 277673 | 160 | 213273 | 45189.1 | 0.0337081 | 0.878991 | 4.00578 | 0.653639 | 0.00301909 | 8.05804e-06 | 7.11268e-06 | 1(Win) | true |
| simdjson (ondemand) | 4535.62 | 0.0862099 | 6589.92ms | 277673 | 320 | 810697 | 58384.4 | 0.124995 | 1.12446 | 4.49958 | 0.721679 | 0.00397192 | 1.00163e-06 | 1.46305e-07 | 2(Loss) | true |
