
----
### Github Events Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5953.92 | 0.184736 | 752.761ms | 2158 | 320 | 130.482 | 345.659 | 0.0117543 | 0.962858 | 3.5797 | 0.517609 | 0.000925336 | 2.02734e-05 | 1.15848e-05 | 1(Win) | true |
| simdjson (ondemand) | 5293.77 | 0.0660383 | 756.721ms | 2158 | 2560 | 168.735 | 388.764 | 0.107697 | 1.06251 | 3.97776 | 0.511585 | 0.000463392 | 3.36683e-05 | 1.61101e-05 | 2(Loss) | true |
