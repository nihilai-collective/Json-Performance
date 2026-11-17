
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3930.44 | 0.0518624 | 235.857ms | 9578 | 80 | 116.215 | 2323.99 | 0.0209813 | 0.622437 | 1(Win) | true |
| simdjson (reflection) | 3808.26 | 0.11844 | 244.481ms | 9578 | 40 | 322.818 | 2398.55 | 0.0827573 | 0.643065 | 2(Loss) | true |
| Glaze | 1931.83 | 0.0409007 | 480.209ms | 9578 | 40 | 149.6 | 4728.3 | 0.185768 | 1.27434 | 3(Loss) | true |
