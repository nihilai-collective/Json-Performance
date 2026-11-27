
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9684.37 | 0.0640449 | 7030.81ms | 631514 | 1280 | 2.03049e+06 | 62188.7 | 0.265184 | 0.526782 | 2.67526 | 0.307062 | 0.000699913 | 2.6437e-06 | 2.0771e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 9668.04 | 0.0318439 | 7022.97ms | 631514 | 4890 | 1.92421e+06 | 62293.8 | 0.00487891 | 0.527079 | 2.67465 | 0.306899 | 0.000690223 | 6.67108e-06 | 5.80777e-06 | 2(Loss) | true |
| simdjson (ondemand) | 8423.28 | 0.0590745 | 7948.12ms | 631514 | 320 | 570891 | 71499.3 | 0.0272612 | 0.603208 | 3.00059 | 0.283799 | 0.000641826 | 3.60245e-06 | 2.8305e-06 | 3(Loss) | true |
| simdjson (reflection) | 8208.84 | 0.0390188 | 8227.49ms | 631514 | 4890 | 4.00737e+06 | 73367.1 | 0.0537698 | 0.621796 | 2.9924 | 0.285764 | 0.00070769 | 1.20368e-05 | 1.12159e-05 | 4(Loss) | true |
| Glaze | 3863.53 | 0.108927 | 8343.47ms | 631514 | 30 | 864939 | 155883 | 0.0851149 | 1.30729 | 5.82639 | 0.956019 | 0.00145418 | 2.655e-05 | 2.47553e-05 | 5(Loss) | true |
