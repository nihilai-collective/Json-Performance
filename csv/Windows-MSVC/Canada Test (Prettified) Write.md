
----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 2694.05 | 1.20747 | 6873.92ms | 6661989 | 80 | 6.48691e+10 | 2.3583e+06 | 4.61086 | 1.12805 | -(Win) | false |
| Glaze | 1319.47 | 0.800082 | 7224.41ms | 6661897 | 30 | 4.45236e+10 | 4.81504e+06 | 2.1593 | 2.30326 | 2(Loss) | true |
