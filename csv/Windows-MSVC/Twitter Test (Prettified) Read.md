
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13541.7 | 0.0195022 | 4452.4ms | 631514 | 4890 | 367869 | 44474.3 | 0.0235805 | 0.224237 | 1(Win) | true |
| simdjson (stage-1) | 12840.8 | 0.131987 | 4695.93ms | 631514 | 640 | 2.45259e+06 | 46902 | 0.0749006 | 0.236489 | 2(Loss) | true |
