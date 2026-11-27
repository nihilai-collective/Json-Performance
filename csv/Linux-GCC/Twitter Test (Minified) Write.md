
----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15593 | 0.0592577 | 3697.38ms | 475954 | 160 | 47608.1 | 29109.6 | 0.117776 | 0.324479 | 1.05401 | 0.138763 | 0.000265729 | 0.00377393 | 6.19808e-06 | 1(Win) | true |
| simdjson (reflection) | 12505.1 | 0.111504 | 4385.82ms | 475954 | 4890 | 8.01024e+06 | 36297.5 | 0.0242856 | 0.397777 | 1.27104 | 0.180557 | 0.000267574 | 0.00225494 | 4.58363e-06 | 2(Loss) | true |
| Glaze | 7451.62 | 0.247644 | 6918.32ms | 475954 | 2560 | 5.82538e+07 | 60913.6 | 0.201757 | 0.679761 | 2.22757 | 0.324927 | 0.000262646 | 0.0141709 | 6.80623e-06 | 3(Loss) | true |
