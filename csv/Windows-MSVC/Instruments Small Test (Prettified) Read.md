
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1722.03 | 0.215124 | 450.276ms | 7932 | 4890 | 436688 | 4392.8 | 0.170778 | 1.42822 | 1(Win) | true |
| Jsonifier | 1545.89 | 0.167815 | 507.57ms | 7932 | 30 | 2022.99 | 4893.33 | 0.0681663 | 1.59326 | 2(Loss) | true |
| Glaze | 1212.6 | 0.529843 | 619.064ms | 7932 | 640 | 699205 | 6238.28 | 0.0825867 | 2.03134 | 3(Loss) | true |
| simdjson (ondemand) | 1093.14 | 0.175283 | 704.956ms | 7932 | 30 | 4413.79 | 6920 | 0.0962464 | 2.25559 | 4(Loss) | true |
