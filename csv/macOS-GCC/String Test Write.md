
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1370.53 | 0.537939 | 719.549ms | 9578 | 640 | 822661 | 6664.8 | 2.06888 | 1(Win) | true |
| simdjson (reflection) | 1124.91 | 1.16677 | 799.098ms | 9578 | 160 | 1.43616e+06 | 8120 | 0.256815 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 920.202 | 1.96428 | 918.121ms | 9578 | 40 | 1.52073e+06 | 9926.4 | 5.94262 | -(Loss) | false |
