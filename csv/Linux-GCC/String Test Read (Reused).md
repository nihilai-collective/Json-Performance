
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1909.25 | 0.35603 | 251.347ms | 4215 | 320 | 17980.2 | 2105.41 | 0.0552455 | 1.28083 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1269.44 | 0.0572687 | 354.807ms | 4215 | 80 | 263.086 | 3166.55 | 0.309651 | 1.93401 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1257.45 | 0.488196 | 357.908ms | 4215 | 320 | 77938.1 | 3196.72 | 0.0966766 | 1.95304 | 2(Tie) | true |
| simdjson (ondemand) | 805.089 | 0.0926031 | 533.452ms | 4215 | 80 | 1710.21 | 4992.91 | 0.0117653 | 3.05967 | 4(Loss) | true |
