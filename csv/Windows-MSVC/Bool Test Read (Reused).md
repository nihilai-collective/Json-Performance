
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 594.072 | 0.135932 | 149.602ms | 905 | 640 | 2495.99 | 1452.81 | 0.55615 | 4.08628 | 1(Win) | true |
| Glaze | 533.071 | 0.311335 | 166.97ms | 905 | 320 | 8130.78 | 1619.06 | 0.250289 | 4.55917 | 2(Loss) | true |
| simdjson (ondemand) | 159.681 | 0.0925069 | 556.653ms | 905 | 40 | 1000 | 5405 | 0.0308261 | 15.4117 | 3(Loss) | true |
