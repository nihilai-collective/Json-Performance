
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1738.3 | 0.229915 | 5163.56ms | 183677 | 1280 | 6.87082e+07 | 100770 | 0.248556 | 1.74798 | 1(Win) | true |
| simdjson (ondemand) | 1420.05 | 0.227658 | 6307.8ms | 183677 | 1280 | 1.00944e+08 | 123353 | 0.096107 | 2.13976 | 2(Loss) | true |
