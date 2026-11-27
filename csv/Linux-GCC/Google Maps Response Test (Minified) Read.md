
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1906.66 | 0.256442 | 618.342ms | 11812 | 640 | 146912 | 5908.12 | 0.238034 | 1.2928 | 1(Win) | true |
| Jsonifier (two-stage) | 1539.43 | 0.180798 | 718.804ms | 11812 | 4890 | 855894 | 7317.5 | 0.0675247 | 1.60208 | 2(Loss) | true |
| Glaze | 1471.4 | 0.121227 | 770.785ms | 11812 | 40 | 3445.43 | 7655.82 | 0.020359 | 1.67672 | 3(Loss) | true |
| simdjson (reflection) | 1433.2 | 0.28271 | 779.755ms | 11812 | 1280 | 632018 | 7859.91 | 0.376681 | 1.72142 | 4(Loss) | true |
| simdjson (ondemand) | 1200.86 | 0.315996 | 948.788ms | 11812 | 320 | 281176 | 9380.63 | 0.00099941 | 2.05573 | 5(Loss) | true |
