
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2825.76 | 0.184351 | 1185.72ms | 11812 | 640 | 34566.1 | 3986.47 | 0.116034 | 1.8078 | 9.06231 | 1.53242 | 0.00306508 | 2.38105e-05 | 5.68807e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2007.65 | 0.076773 | 1356.02ms | 11812 | 2560 | 47503.7 | 5610.94 | 0.0148588 | 2.53639 | 12.5033 | 2.07653 | 0.00460836 | 4.4744e-05 | 2.10326e-05 | 2(Loss) | true |
| Glaze | 2000.83 | 0.106617 | 1355.48ms | 11812 | 1280 | 46119.4 | 5630.05 | 0.0600794 | 2.54521 | 12.6057 | 2.41246 | 0.00109165 | 2.91679e-05 | 9.45807e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1119.71 | 0.0498383 | 1846.54ms | 11812 | 4890 | 122934 | 10060.5 | 0.0470121 | 4.53122 | 19.6591 | 3.21851 | 0.00732232 | 2.63501e-05 | 8.39672e-06 | 4(Loss) | true |
