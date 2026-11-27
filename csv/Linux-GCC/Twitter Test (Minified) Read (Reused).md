
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3048.76 | 0.0696038 | 9306.47ms | 466906 | 1280 | 1.32278e+07 | 146051 | 0.250194 | 1.63756 | 5.18698 | 0.876202 | 0.00756197 | 0.00227771 | 1.40954e-05 | 1(Win) | true |
| Glaze | 2252.47 | 0.224252 | 5987.43ms | 466906 | 160 | 3.14437e+07 | 197683 | 0.063073 | 2.22592 | 8.99193 | 1.54406 | 0.00655748 | 0.0026751 | 3.96895e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2033.58 | 0.179575 | 6456.72ms | 466906 | 320 | 4.94744e+07 | 218962 | 0.116639 | 2.45862 | 7.9594 | 1.16669 | 0.0167803 | 0.0069382 | 2.27495e-05 | 3(Loss) | true |
| simdjson (reflection) | 1875.12 | 0.337961 | 7059.15ms | 466906 | 80 | 5.15256e+07 | 237465 | 0.254816 | 2.66157 | 9.0508 | 1.26695 | 0.00790031 | 0.0187926 | 2.7709e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1333.11 | 0.229767 | 9434.63ms | 466906 | 160 | 9.42378e+07 | 334014 | 0.000338682 | 3.7679 | 11.7593 | 2.43232 | 0.0105762 | 0.00930597 | 1.16324e-05 | 5(Loss) | true |
