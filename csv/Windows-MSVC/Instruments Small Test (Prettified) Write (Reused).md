
----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11268.3 | 0.488761 | 85.2416ms | 9249 | 2560 | 37471.8 | 782.773 | 0.79703 | 0.2114 | 1(Win) | true |
| Glaze | 3830.85 | 0.108578 | 244.213ms | 9249 | 40 | 250 | 2302.5 | 0.253991 | 0.637982 | 2(Loss) | true |
