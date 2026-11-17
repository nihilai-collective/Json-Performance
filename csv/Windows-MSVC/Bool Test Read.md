
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 611.568 | 0.128668 | 142.346ms | 905 | 1280 | 4220.48 | 1411.25 | 0.132685 | 4.90461 | 1(Win) | true |
| Glaze | 601.45 | 0.121491 | 145.499ms | 905 | 4890 | 14862.6 | 1434.99 | 0.0986124 | 4.98487 | 2(Loss) | true |
| Jsonifier (two-stage) | 261.05 | 0.121694 | 330.361ms | 905 | 1280 | 20720.3 | 3306.17 | 0.0637604 | 11.5845 | 3(Loss) | true |
| simdjson (ondemand) | 122.106 | 0.0859617 | 703.471ms | 905 | 2560 | 94508.8 | 7068.24 | 0.0613816 | 24.8219 | 4(Loss) | true |
