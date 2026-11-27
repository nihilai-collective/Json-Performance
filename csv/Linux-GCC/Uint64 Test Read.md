
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1536.74 | 0.170275 | 78.5842ms | 1213 | 30 | 49.2885 | 752.767 | 0.00885544 | 1.55109 | 1(Win) | true |
| simdjson (reflection) | 971.182 | 0.122869 | 120.286ms | 1213 | 30 | 64.2575 | 1191.13 | 0.170415 | 2.49132 | 2(Loss) | true |
| Glaze | 938.871 | 0.0906093 | 125.633ms | 1213 | 40 | 49.8558 | 1232.12 | 0.0263842 | 2.58007 | 3(Loss) | true |
| simdjson (ondemand) | 304.968 | 0.462038 | 384.951ms | 1213 | 320 | 98291.9 | 3793.2 | 0.657929 | 8.05955 | 4(Loss) | true |
