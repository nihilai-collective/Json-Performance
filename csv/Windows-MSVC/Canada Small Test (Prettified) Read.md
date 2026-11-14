
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 430.046 | 0.154551 | 2607.72ms | 11579 | 1280 | 2.01588e+06 | 25677.7 | 0.160691 | 5.75021 | 1(Win) | true |
| simdjson (ondemand) | 405.87 | 0.141094 | 2733.38ms | 11579 | 2560 | 3.77245e+06 | 27207.2 | 0.287896 | 6.09375 | 2(Loss) | true |
