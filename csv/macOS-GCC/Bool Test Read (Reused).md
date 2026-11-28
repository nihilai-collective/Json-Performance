
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1656.89 | 1.42246 | 51.924ms | 905 | 4890 | 268472 | 520.9 | 0.0959349 | 1(Win) | true |
| Glaze | 1508.35 | 2.43167 | 59.4281ms | 905 | 1280 | 247808 | 572.2 | 0.452331 | 2(Loss) | true |
| simdjson (reflection) | 933.155 | 0.776763 | 97.4769ms | 905 | 2560 | 132132 | 924.9 | 0.226537 | 3(Loss) | true |
| simdjson (ondemand) | 368.866 | 0.368681 | 227.448ms | 905 | 4890 | 363891 | 2339.81 | 0.0388468 | 4(Loss) | true |
