
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9106.17 | 0.108306 | 6617.38ms | 631514 | 2560 | 1.31352e+07 | 66137.4 | 0.318532 | 0.271723 | 1(Win) | true |
| Jsonifier | 8776.6 | 0.286377 | 6726.23ms | 631514 | 320 | 1.23578e+07 | 68620.9 | 0.050575 | 0.281951 | 2(Loss) | true |
| simdjson (ondemand) | 4947.69 | 0.232662 | 6254.79ms | 631514 | 640 | 5.13325e+07 | 121725 | 0.0353123 | 0.500264 | 3(Loss) | true |
| Glaze | 3481.06 | 0.289877 | 9009.68ms | 631514 | 80 | 2.01214e+07 | 173010 | 0.115734 | 0.711079 | 4(Loss) | true |
