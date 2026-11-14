
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 6854.92 | 0.125857 | 771.241ms | 3808 | 4890 | 2173.96 | 529.779 | 0.11798 | 0.802783 | 3.25341 | 0.31854 | 0.000314804 | 2.48642e-05 | 1.22979e-05 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 6851.09 | 0.14727 | 772.506ms | 3808 | 160 | 97.5038 | 530.075 | 0.157747 | 0.808805 | 3.24422 | 0.323529 | 0.00026917 | 6.56513e-06 | 0 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 6669.72 | 0.0995247 | 782.153ms | 3808 | 640 | 187.94 | 544.489 | 0.263265 | 0.828928 | 3.25289 | 0.371061 | 0.000262605 | 2.70811e-05 | 1.23096e-05 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6653 | 0.175224 | 779.688ms | 3808 | 2560 | 2341.99 | 545.858 | 0.0822204 | 0.828995 | 3.25289 | 0.371061 | 0.000263323 | 4.20578e-05 | 2.02083e-05 | 3(Tie) | true |
| Glaze | 3565.89 | 0.0962162 | 822.752ms | 3808 | 160 | 153.63 | 1018.42 | 0.131158 | 1.50122 | 6.53151 | 1.19433 | 0.000344669 | 2.95431e-05 | 0 | 5(Loss) | true |
