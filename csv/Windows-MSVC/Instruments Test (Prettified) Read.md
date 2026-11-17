
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21499.6 | 0.0981454 | 837.803ms | 183677 | 40 | 2557.69 | 8147.5 | 0.112383 | 0.114782 | 1(Win) | true |
| simdjson (stage-1) | 19296.9 | 0.100467 | 915.121ms | 183677 | 40 | 3326.92 | 9077.5 | 0.027533 | 0.127716 | 2(Loss) | true |
