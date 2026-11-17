
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25130.6 | 0.256756 | 5295.15ms | 5373214 | 80 | 2.19277e+07 | 203906 | 0.182401 | 0.0985066 | 1(Win) | true |
| simdjson (stage-1) | 19620.7 | 0.305365 | 6880.26ms | 5373214 | 40 | 2.54412e+07 | 261168 | 0.161395 | 0.126164 | 2(Loss) | true |
