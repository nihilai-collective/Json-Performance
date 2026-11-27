
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1906.68 | 0.104468 | 9565.04ms | 5373214 | 160 | 1.26124e+09 | 2.68755e+06 | 0.243061 | 1.29846 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1902.85 | 0.135039 | 9647.96ms | 5373214 | 30 | 3.9673e+08 | 2.69296e+06 | 0.0462828 | 1.30108 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1805.63 | 0.112079 | 10113.6ms | 5373214 | 160 | 1.61875e+09 | 2.83796e+06 | 0.810077 | 1.37114 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1770.57 | 1.19838 | 10100.4ms | 5373214 | 40 | 4.81165e+10 | 2.89416e+06 | 0.574201 | 1.39829 | 3(Tie) | true |
| Glaze | 1726.77 | 0.0876541 | 5110.8ms | 5373214 | 80 | 5.41292e+08 | 2.96755e+06 | 0.0913857 | 1.43375 | 5(Loss) | true |
