
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 949.039 | 0.088371 | 8202.17ms | 2251027 | 40 | 1.59836e+08 | 2.26202e+06 | 1.06533 | 2.60871 | 1(Win) | true |
| Jsonifier (two-stage) | 882.42 | 0.111134 | 8725.21ms | 2251027 | 160 | 1.16956e+09 | 2.4328e+06 | 0.0251643 | 2.80566 | 2(Loss) | true |
| Glaze | 850.487 | 0.206277 | 9037.84ms | 2251027 | 160 | 4.33756e+09 | 2.52414e+06 | 0.163262 | 2.911 | 3(Loss) | true |
| simdjson (ondemand) | 802.829 | 0.0910973 | 9506.47ms | 2251027 | 30 | 1.78012e+08 | 2.67398e+06 | 0.111164 | 3.08381 | 4(Loss) | true |
| simdjson (reflection) | 795.603 | 0.15431 | 9431.28ms | 2251027 | 30 | 5.20091e+08 | 2.69826e+06 | 0.606058 | 3.11181 | 5(Loss) | true |
